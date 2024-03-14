import 'package:flutter/material.dart';
import 'package:windows_channel/windows_channel.dart';

class HomeWidget extends StatelessWidget {
  const HomeWidget({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Demo Windows Channel'),
      ),
      body: Column(
        children: <Widget>[
          ElevatedButton(
            onPressed: () {
              WindowsChannel.instance.onEvent01(arg01: 10, arg02: "Um texto qualquer.");
            },
            child: Text("Evento 01"),
          ),
          ElevatedButton(
            onPressed: () {
              WindowsChannel.instance.onEvent02();
            },
            child: Text("Evento 02"),
          ),
          ElevatedButton(
            onPressed: () {
              WindowsChannel.instance.onEvent03();
            },
            child: Text("Evento 03"),
          ),
        ],
      ),
    );
  }
}
