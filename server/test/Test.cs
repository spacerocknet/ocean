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
		private int id = 100;
		public TcpClient client;
		public Stream stream;
		public Client(string host, int port)
		{
			client= new TcpClient();
			client.Connect(host,port);
			stream = client.GetStream ();
		}

		void Close()
		{
			stream.Close ();
			client.Close();
		}
		public string HttpRequest(int type, string message)
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

		public string TcpRequest(int type, string data)
		{
			byte[] buf = EncodeMessage (id++, type, data);
			stream.Write(buf,0,buf.Length);
			byte[] bb=new byte[1024];
			int k = stream.Read(bb,0,1024);
			string s = DecodeMessage(bb, k);
			return s;
		}

		public byte[] EncodeMessage(int message_id, int type, string data)
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
		public string DecodeMessage(byte[] data, int length)
		{
			int offset = 8;
			int size = ((int)data[2]<<8) + data[3];
			if (data [7] == 2) offset += 8;

			byte[] content = new byte[size];
			Array.Copy (data, offset, content, 0, size);
			string s = Encoding.UTF8.GetString(content, 0, content.Length);
			return s;
		}

		public void SayHello()
		{
			string text = HttpRequest (1, "{\"text\":\"NGUYEN Hong San\"}");
			Console.WriteLine (text);
		}

		public void PingPong()
		{
			string text = TcpRequest (2, "{\"text\":\"PING\"}");
			Console.WriteLine (text);
		}

		public static void Main (string[] args)
		{
			Client c = new Client ("127.0.0.1", 5678);
			c.SayHello();
			c.PingPong();
			c.Close ();
		}
	}
}
