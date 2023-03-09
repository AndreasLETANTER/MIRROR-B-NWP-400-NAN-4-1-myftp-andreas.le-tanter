#!/bin/bash 

if [ "$#" -ne 2 ]; then
    echo "USAGE: $0 host port"
    exit 0
fi

USERNAME="Anonymous"
PASS=""

HOST=$1
PORT=$2
MKFIFO=`which mkfifo`
PIPE=fifo
OUT=outfile
TAIL=`which tail`
NC="`which nc` -C"
TIMEOUT=0 #max time before reading server response

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
CLEAR='\033[0m'


getcode()
{
  sleep $TIMEOUT
  local code=$1
  printf "${BLUE}Waiting for $code reply-code\n${CLEAR}"
  local data=`$TAIL -n 1 $OUT |cat -e |grep "^$code.*[$]$" |wc -l`
  return $data
}

print_failed()
{
    printf "${RED}$1 test failed\n"
    printf "Expected reply-code: $2\n"
    printf "Received : ["`$TAIL -n 1 $OUT| cat -e`"]\n"
    printf "KO\n${CLEAR}"
}

print_succeeded()
{
  printf "${GREEN}$1 test succeeded\n"
  printf "OK\n${CLEAR}"  
  kill_client 2>&1 >/dev/null
}

launch_client()
{
  local host=$1
  local port=$2

  $MKFIFO $PIPE
  ($TAIL -f $PIPE 2>/dev/null | $NC $host $port &> $OUT &) >/dev/null 2>/dev/null

  printf "${BLUE}Connecting to $host : $port\n${CLEAR}"
  sleep $TIMEOUT
  getcode 220
  if [[ $? -eq 1 ]]; then
    printf "${GREEN}Reply-code OK\n${CLEAR}"
    return 1
  else
    printf "${RED}Connection to $host:$port failed\n"
    printf "Expected reply-code: 220\n"
    printf "Received : ["`tail -n 1 $OUT |cat -e`"]${CLEAR}\n"
    return 0
  fi  
}

launch_test()
{
  local test_name=$1
  local cmd=$2
  local code=$3

  printf "${BLUE}Sending [$cmd^M$]${CLEAR}\n"
  echo "$cmd" >$PIPE
  getcode $code
  if [[ ! $? -eq 1 ]]; then
    print_failed "$test_name" "$code"
    kill_client
    clean
  fi
  printf "${GREEN}Reply-code OK${CLEAR}\n"
}

kill_client()
{
  local nc=`which nc`

  if [ `pidof $TAIL | wc -l` -ne 0 ]
  then
    killall $TAIL &>/dev/null
  fi
  if [ `pidof $nc | wc -l` -ne 0 ]
  then
    killall $nc &>/dev/null
  fi  
  rm -f $PIPE $OUT &> /dev/null
}

clean()
{
  rm -f $PIPE $OUT log &>/dev/null
}

init()
{
  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill_client
    return
  fi
}

test00()
{
  init

  local test_name="Bad Authentication password"
  local cmd1="USER $USERNAME"
  local cmd2="PASS aeez"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 530

  print_succeeded "$test_name"
  clean
  return
}

test01()
{
  init

  local test_name="Authentication"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230

  print_succeeded "$test_name"
  clean
  return
}

test02()
{
  init

  local test_name="Bad Authentication Username"
  local cmd1="USER azeazeazea"
  local cmd2="PASS $PASS"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 530

  print_succeeded "$test_name"
  clean
  return
}

test03()
{
  init

  local test_name="PASS Command before USER"
  local cmd1="USER azeazeazea"
  local cmd2="PASS $PASS"
  launch_test "$test_name" "$cmd2" 332
  launch_test "$test_name" "$cmd1" 331

  print_succeeded "$test_name"
  clean
  return
}

test04()
{
  init

  local test_name="QUIT Command basic"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="QUIT"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 221

  print_succeeded "$test_name"
  clean
  return
}

test05()
{
  init

  local test_name="QUIT Command basic with not wanted param"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="QUIT azeazeaze"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test06()
{
  init

  local test_name="NOOP Command basic"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="NOOP"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 200

  print_succeeded "$test_name"
  clean
  return
}

test07()
{
  init

  local test_name="CDUP Command basic"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="CDUP"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 200

  print_succeeded "$test_name"
  clean
  return
}

test07()
{
  init

  local test_name="CDUP Command basic with not wanted param"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="CDUP azeazeaze"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test08()
{
  init

  local test_name="PWD Command basic with not wanted param"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="PWD azeazeaze"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test09()
{
  init

  local test_name="PWD Command basic"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="PWD"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 257

  print_succeeded "$test_name"
  clean
  return
}

test10()
{
  init

  local test_name="DELE Command basic"
  touch tempDELE
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="DELE tempDELE"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 250

  print_succeeded "$test_name"
  clean
  return
}

test11()
{
  init

  local test_name="DELE Command basic but no file"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="DELE tempDELE"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 550

  print_succeeded "$test_name"
  clean
  return
}

test12()
{
  init

  local test_name="DELE Command basic but not wanted param"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="DELE tempDELE azeazeaze"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test13()
{
  init

  local test_name="Bad Command"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="testeeqd"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test14()
{
  init

  local test_name="Command before login"
  local cmd3="testeeqd"
  launch_test "$test_name" "$cmd3" 530

  print_succeeded "$test_name"
  clean
  return
}

test15()
{
  init

  local test_name="Only space"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="      "
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 500

  print_succeeded "$test_name"
  clean
  return
}

test16()
{
  init

  local test_name="Basic CWD command"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="CWD src/"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 250

  print_succeeded "$test_name"
  clean
  return
}

test17()
{
  init

  local test_name="Basic CWD command with bad path"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="CWD src/eazeaze"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 550

  print_succeeded "$test_name"
  clean
  return
}

test18()
{
  init

  local test_name="Basic CWD command with .."
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="CWD .."
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 250

  print_succeeded "$test_name"
  clean
  return
}

test19()
{
  init

  local test_name="Basic PASV"
  local cmd1="USER Anonymous"
  local cmd2="PASS "
  local cmd3="PASV"
  launch_test "$test_name" "$cmd1" 331
  launch_test "$test_name" "$cmd2" 230
  launch_test "$test_name" "$cmd3" 227

  print_succeeded "$test_name"
  clean
  return
}

test00
test01
test02
test03
test04
test05
test06
test07
test08
test09
test10
test11
test12
test13
test14
test15
test16
test17
test18
test19
clean