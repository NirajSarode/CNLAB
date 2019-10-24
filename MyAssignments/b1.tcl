set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue

set nf [open tcp_b1.nam w]
$ns namtrace-all $nf

set trc [open trace.tr w]
$ns trace-all $trc


proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam tcp_b1.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail

$ns queue-limit $n1 $n2 7

$ns duplex-link-op $n0 $n1 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 2

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

$ns at 0.1 "$ftp start"
$ns at 4.0 "$ftp stop"

$ns at 4.5 "finish"

$ns run
