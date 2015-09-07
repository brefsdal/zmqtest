package zmqtest

import org.zeromq.ZMQ

/**
 * Created by brianrefsdal on 9/6/15.
 */
object Publisher {
  def main (args: Array[String]) {

    if (args.length < 3) {
      val name = Publisher.getClass.getName
      println(s"Usage: ${name} host port")
    }

    val ctx = ZMQ.context(1)
    val subscriber = ctx.socket(ZMQ.SUB)
    subscriber.connect("tcp://localhost:9000")
    subscriber.subscribe("".getBytes())
    0 until 100 foreach { ii =>
      val str = subscriber.recvStr(0).trim()
      println(str)
    }
    subscriber.close()
    ctx.term()
  }
}
