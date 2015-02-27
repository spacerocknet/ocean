using System;
using System.Net;
using System.IO;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using comm;

namespace Ocean
{
	class Client
	{
		Session session;
		public Client()
		{
			session = new Session ();
		}

		public void Close()
		{
			if (session.IsOpened ()) session.Close ();
		}
		public Session Session()
		{
			return session;
		}
		public byte[] SendHttpRequest(int type, byte[] data)
		{
			string url = "http://127.0.0.1:8088/ocean/r/" + type;
			var request = System.Net.HttpWebRequest.Create(url);
			request.Method ="POST";
			request.ContentType = "application/json";
			var requestStream = request.GetRequestStream();
			requestStream.Write(data, 0, data.Length);
			requestStream.Close ();

			HttpWebResponse response = (HttpWebResponse)request.GetResponse ();

			Stream receiveStream = response.GetResponseStream();

			using (MemoryStream ms = new MemoryStream())
			{
				receiveStream.CopyTo(ms);
				return ms.ToArray();
			}
		}

		public void SayHello()
		{
			HelloRequest.Builder tmp = HelloRequest.CreateBuilder ();
			tmp.SetName ("NGUYEN Hong San");
			HelloRequest req = tmp.BuildPartial();
			MemoryStream stream = new MemoryStream ();
			req.WriteTo(stream);
			byte[] data1 = stream.ToArray();
			byte[] data2 = SendHttpRequest (1, data1);
			HelloReply rep  = HelloReply.CreateBuilder().MergeFrom(data2).BuildPartial();
			Console.WriteLine (rep.Text);
		}

		public static void Main (string[] args)
		{
			Client c = new Client ();
			c.SayHello();
			Session s = c.Session ();
			s.Open ("127.0.0.1", 5678);
			s.PingPong ();
			c.Close ();
		}
	}
}
