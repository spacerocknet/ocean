using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;

namespace test_ocean
{
	class OceanClient
	{
		public TcpClient client;
		Stream stream;
		OceanClient()
		{
			client= new TcpClient();
			Console.WriteLine("Connecting.....");
			client.Connect("127.0.0.1",5678);
			Console.WriteLine("Connected");
			stream = client.GetStream ();
		}

		void Close()
		{
			client.Close();
		}
		public void SayHello(string name)
		{
			var request = System.Net.HttpWebRequest.Create("http://127.0.0.1:8088/ocean/r/1");
			request.Method ="POST";
			request.ContentType = "application/json";
			var requestStream = request.GetRequestStream();
			string r = "{\"text\":\"NGUYEN Hong San\"}";

			byte[] bytes = Encoding.UTF8.GetBytes(r);

			requestStream.Write(bytes, 0, bytes.Length);
			requestStream.Close ();
			HttpWebResponse response = (HttpWebResponse)request.GetResponse ();
			Stream receiveStream = response.GetResponseStream();
			StreamReader reader = new StreamReader(receiveStream);
			string text = reader.ReadToEnd ();
			Console.WriteLine (text);
		}

		public byte[] encode_message(int message_id, int type, string data)
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
		public string decode_message(byte[] data, int length)
		{
			int offset = 8;
			int size = ((int)data[2]<<8) + data[3];
			if (data [7] == 2) offset += 8;

			byte[] content = new byte[size];
			Array.Copy (data, offset, content, 0, size);
			string s = Encoding.UTF8.GetString(content, 0, content.Length);
			return s;
		}

		public void PingPong()
		{
			byte[] msg = this.encode_message (1234, 2, "{\"text\":\"PING\"}");
			stream.Write(msg,0,msg.Length);

			byte[] bb=new byte[1024];
			int k = stream.Read(bb,0,1024);
			string s = decode_message (bb, k);
			Console.WriteLine (s);
		}

		public static void Main (string[] args)
		{
			OceanClient c = new OceanClient ();
			c.SayHello("NGUYEN Hong San");
			c.PingPong();
			c.Close ();
		}
	}
}
