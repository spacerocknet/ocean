using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace Ocean
{
	class Client
	{
		const int HEADER_LENGTH = 8;
		const byte PACKET_MAGIC = 0xEE;
		private Int64 id = 100;
		public TcpClient client;
		public Stream stream;
		private Thread thread;
		public Client(string host, int port)
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
					Int64 mid = 0;
					int offset = 8;
					if ((header[7] & 0x02)==2)
					{						
						mid += content[offset++]; //0
						mid <<= 8;
						mid += content[offset++]; //1
						mid <<= 8;
						mid += content[offset++]; //2
						mid <<= 8;
						mid += content[offset++]; //3
						mid <<= 8;
						mid += content[offset++]; //4
						mid <<= 8;
						mid += content[offset++]; //5
						mid <<= 8;
						mid += content[offset++]; //6
						mid <<= 8;
						mid += content[offset++]; //7
					}
					byte[] buf = new byte[size - offset];
					Array.Copy (content, offset, buf, 0, buf.Length);
					string s = Encoding.UTF8.GetString(buf, 0, buf.Length);
					this.MessageReceived (type, mid, s); 
					received = 0;
					size = 0;
					type = 0;
				}
			}
		}

		public void MessageReceived(int type, Int64 id, string data)
		{
			Console.WriteLine ("Message received:"+data);
		}

		public void Close()
		{
			thread.Abort ();
			stream.Close ();
			client.Close();
		}
		public string SendHttpRequest(int type, string message)
		{
			string url = "http://127.0.0.1:8088/ocean/r/" + type;
			var request = System.Net.HttpWebRequest.Create(url);
			request.Method ="POST";
			request.ContentType = "application/json";
			var requestStream = request.GetRequestStream();
			byte[] bytes = Encoding.UTF8.GetBytes(message);
			requestStream.Write(bytes, 0, bytes.Length);
			requestStream.Close ();

			HttpWebResponse response = (HttpWebResponse)request.GetResponse ();
			Stream receiveStream = response.GetResponseStream();
			StreamReader reader = new StreamReader(receiveStream);
			string text = reader.ReadToEnd ();
			return text;
		}

		public string SendTcpRequest(int type, string data)
		{
			byte[] buf = EncodeMessage (id++, type, data);
			stream.Write(buf,0,buf.Length);
			return "PONG";
		}

		public byte[] EncodeMessage(Int64 message_id, int type, string data)
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

			if (message_id > 0)
			{
				buf[7] += 2;
				buf[offset++] = (byte)((message_id >> 56) & 0xFF);
				buf[offset++] = (byte)((message_id >> 48) & 0xFF);
				buf[offset++] = (byte)((message_id >> 40) & 0xFF);
				buf[offset++] = (byte)((message_id >> 32) & 0xFF);
				buf[offset++] = (byte)((message_id >> 24) & 0xFF);
				buf[offset++] = (byte)((message_id >> 16) & 0xFF);
				buf[offset++] = (byte)((message_id >> 8) & 0xFF);
				buf[offset++] = (byte)(message_id & 0xFF);
			}

			byte[] bytes = Encoding.UTF8.GetBytes(data);
			Array.Copy (bytes, 0, buf, offset, bytes.Length);
			return buf;
		}

		public void SayHello()
		{
			string text = SendHttpRequest (1, "{\"text\":\"NGUYEN Hong San\"}");
			Console.WriteLine (text);
		}

		public void PingPong()
		{
			string text = SendTcpRequest (2, "{\"text\":\"PING\"}");
			Console.WriteLine (text);
		}

		public static void Main (string[] args)
		{
			Client c = new Client ("127.0.0.1", 5678);
			c.SayHello();
			c.PingPong();
			Thread.Sleep (2000);
			c.Close ();
		}
	}
}
