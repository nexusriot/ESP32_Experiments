examples:

$ curl -i -X GET http://192.168.0.166
$ curl -i -X GET http://192.168.0.166/networks
$ curl -i -X GET http://192.168.0.166/get-query-param?query-param=HelloServer
$ curl -i -d '{"message":"My data"}'  -H "Content-Type: application/json"  -X POST http://192.168.0.166/post-message


