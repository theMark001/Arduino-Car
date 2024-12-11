import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

class ControlCarScreen extends StatefulWidget {
  const ControlCarScreen({Key? key}) : super(key: key);

  @override
  _ControlCarScreenState createState() => _ControlCarScreenState();
}

class _ControlCarScreenState extends State<ControlCarScreen> {
  BluetoothCharacteristic? characteristic;

  void connectToHC05() async {
    FlutterBluePlus.startScan(timeout: const Duration(seconds: 4));

    FlutterBluePlus.scanResults.listen((results) async {
      for (ScanResult result in results) {
        if (result.device.platformName == "HC-05") {
          FlutterBluePlus.stopScan();
          await result.device.connect();
          
          // Discover services
          List<BluetoothService> services =
              await result.device.discoverServices();
          for (var service in services) {
            for (var c in service.characteristics) {
              if (c.properties.write) {
                setState(() {
                  characteristic = c;
                });
                break;
              }
            }
          }
          break;
        }
      }
    });
  }

  void sendCommand(String command) async {
    if (characteristic != null) {
      await characteristic!.write(command.codeUnits);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Control Car'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            ElevatedButton(
              onPressed: connectToHC05,
              child: const Text('Connect to HC-05'),
            ),
            ElevatedButton(
              onPressed: () => sendCommand('f'),
              child: const Text('Forward'),
            ),
            ElevatedButton(
              onPressed: () => sendCommand('b'),
              child: const Text('Backward'),
            ),
            ElevatedButton(
              onPressed: () => sendCommand('l'),
              child: const Text('Left'),
            ),
            ElevatedButton(
              onPressed: () => sendCommand('r'),
              child: const Text('Right'),
            ),
            ElevatedButton(
              onPressed: () => sendCommand('q'),
              child: const Text('Stop'),
            ),
          ],
        ),
      ),
    );
  }
}

void main() {
  runApp(MaterialApp(
    home: ControlCarScreen(),
  ));
}