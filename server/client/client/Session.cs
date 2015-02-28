using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using comm;

namespace Ocean
{
	public class Session
	{
		readonly object REPLY_LOCK = new object();
		byte[] received = null;

		const int HEADER_LENGTH = 8;
		const byte PACKET_MAGIC = 0xEE;
		public TcpClient client;
		public Stream stream;
		private Thread thread;

		private string id;
		public string Id
		{ 
			get
			{
				return id;	
			}
		}
		bool running;

		public Session (string id)
		{
			this.id = id;
			running = false;
		}

		public void Open(string host, int port)
		{
			client= new TcpClient();
			client.Connect(host,port);
			stream = client.GetStream ();
			thread = new Thread (new ThreadStart (this.ReadMessage));
			running = true;
			thread.Start ();
		}
		public void Close()
		{
			/*			
 			lock(REPLY_LOCK)
			{
				running = false;
				stream.Close ();
				client.Close ();
			}
			*/
		}

		public bool IsOpened()
		{
			return running;
		}

		private void ReadMessage()
		{
			int received = 0;
			int type=0, size=0;
			byte[] header = new byte[HEADER_LENGTH];
			byte[] content=null;
			while (running) 
			{
				if (received < HEADER_LENGTH) 
				{

					int count = stream.Read (header, received, HEADER_LENGTH - received);
					received += count;
					if (received == HEADER_LENGTH)
					{
						if (header[0] != PACKET_MAGIC || header[1] != PACKET_MAGIC)
						{
							//TODO: handle error
						}
						size = ((int)header[2] << 8) + header[3]; // 2 bytes for size
						type = ((int)header[4] << 16) + ((int)header[5] << 8) + header[6];//3 bytes for type
						content = new byte[size];
						Array.Copy (header, 0, content, 0, HEADER_LENGTH);
					}
				} 
				else if (received < size)
				{
					int count = stream.Read(content, received, size - received);
					received += count;
				}
				else if (received == size) 
				{
					int offset = 8;
					if (header [7] == 2) offset += 8;
					byte[] buf = new byte[size - offset];
					Array.Copy (content, offset, buf, 0, buf.Length);

					if (type == 0) /* reply message */ 
					{ 
						lock (REPLY_LOCK) 
						{
							this.received = buf;
							Monitor.PulseAll (REPLY_LOCK);
						}
					} 
					else /* notification message */
					{
						this.NotificationReceived (type, buf); 
					}
					received = 0;
				}
			}
			Console.WriteLine ("End of loop");
		}

		public void NotificationReceived(int type, byte[] data)
		{
			Console.WriteLine ("Notification received");
			/* TODO: process notification here */
		}

		public byte[] SendTcpRequest(int type, byte[] data)
		{
			/*TODO: add lock here for synchonization and thread-safe*/

			/* encode message */ 
			int size = HEADER_LENGTH + data.Length;
			byte[] buf = new byte[size];
			buf[0] = 0xEE;
			buf[1] = 0xEE;

			buf[2] = (byte)((size >> 8) & 0xFF);
			buf[3] = (byte)(size & 0xFF);

			buf[4] = (byte)((type >> 16) & 0xFF);
			buf[5] = (byte)((type >> 8) & 0xFF);
			buf[6] = (byte)(type & 0xFF);
			buf[7] = 0;
			int offset = 8;
			Array.Copy (data, 0, buf, offset, data.Length);
			stream.Write(buf,0,buf.Length);

			/* wait for reply here and return */
			lock (REPLY_LOCK) 
			{
				while (running && received==null) Monitor.Wait (REPLY_LOCK);
				if (!running) return null;
				byte[] ret = received;
				received = null;
				return ret;
			}
		}

		public bool Join(string token)
		{
			JoinSessionRequest.Builder tmp = JoinSessionRequest.CreateBuilder ();
			tmp.SetSid(this.id);
			tmp.SetToken (token);
			JoinSessionRequest req = tmp.BuildPartial();
			MemoryStream stream = new MemoryStream ();
			req.WriteTo(stream);
			byte[] data1 = stream.ToArray();
			byte[] data2 = SendTcpRequest ((int)comm.Service.JOIN_SESSION, data1);
			JoinSessionReply rep  = JoinSessionReply.CreateBuilder().MergeFrom(data2).BuildPartial();
			if (rep.Type == 0) 
			{
				/* TODO: do something with reply data */
				return true;
			} 
			else return false;
		}
	}
}

