using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace Ocean
{
	public class Session
	{
		const int HEADER_LENGTH = 8;
		const byte PACKET_MAGIC = 0xEE;
		public TcpClient client;
		public Stream stream;
		private Thread thread;

		public Session ()
		{
		}

		public bool Open(string host, int port)
		{
			client= new TcpClient();
			client.Connect(host,port);
			stream = client.GetStream ();
			thread = new Thread (new ThreadStart (this.ReadMessage));
			thread.Start ();
		}

		private void ReadMessage()
		{
			int received = 0;
			int type=0, size=0;
			byte[] header = new byte[HEADER_LENGTH];
			byte[] content=null;
			while (true) 
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
						//size = HEADER_LENGTH;
						content = new byte[size];
						Array.Copy (header, 0, content, 0, HEADER_LENGTH);
					}
				} 
				else if (received < size)
				{
					int count = stream.Read(content, received, size - received);
					received += count;
					Console.WriteLine (count);
					Console.WriteLine (received);
					Console.WriteLine (size);
				}
				else if (received == size) 
				{
					int offset = 8;
					byte[] buf = new byte[size - offset];
					Array.Copy (content, offset, buf, 0, buf.Length);
					string s = Encoding.UTF8.GetString(buf, 0, buf.Length);
					this.MessageReceived (type, s); 
					received = 0;
					size = 0;
					type = 0;
				}
			}
		}

		public void MessageReceived(int type, string data)
		{
			Console.WriteLine ("Message received:"+data);
		}

		public void Close()
		{
			thread.Abort ();
			stream.Close ();
			client.Close();
		}

		public string SendTcpRequest(int type, string data)
		{
			int size = 8 + data.Length;
			if (message_id != 0) size += 8;
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
			byte[] bytes = Encoding.UTF8.GetBytes(data);
			Array.Copy (bytes, 0, buf, offset, bytes.Length);
			stream.Write(buf,0,buf.Length);
			return "PONG";
		}

		public void PingPong()
		{
			string text = SendTcpRequest (2, "{\"text\":\"PING\"}");
			Console.WriteLine (text);
		}
	}
}

