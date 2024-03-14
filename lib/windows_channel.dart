import 'package:flutter/services.dart';

class WindowsChannel {
  static const MethodChannel _channel = MethodChannel('um_nome_qualquer_para_o_canal');

  static final WindowsChannel instance = WindowsChannel._();

  WindowsChannel._() {
    _channel.setMethodCallHandler(_methodCallHandler);
  }

  Future<void> _methodCallHandler(MethodCall call) async {
    switch (call.method) {
      case 'nome_do_evento_01':
        return onEvent01(arg01: call.arguments['argIntEvent01'], arg02: call.arguments['argStringEvent01']);
      case 'nome_do_evento_02':
        return onEvent02();
      case 'nome_do_evento_03':
        return onEvent03();
      default:
    }
  }

  Future<void> onEvent01({required int arg01, required String arg02}) async {
    final Map<String, dynamic> arguments = {
      'argIntEvent01': arg01,
      'argStringEvent01': arg02,
    };
    await _channel.invokeMethod('nome_do_evento_01', arguments);
  }

  Future<void> onEvent02() async {
    await _channel.invokeMethod('nome_do_evento_02');
  }

  Future<void> onEvent03() async {
    await _channel.invokeMethod('nome_do_evento_03');
  }
}
