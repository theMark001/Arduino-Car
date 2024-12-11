import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:four_dir/main.dart';

void main() {
  testWidgets('Test app loads ControlCarScreen', (WidgetTester tester) async {
    // Build the app and trigger a frame.
    await tester.pumpWidget(const MaterialApp(home: ControlCarScreen()));

    // Verify if ControlCarScreen is displayed.
    expect(find.byType(ControlCarScreen), findsOneWidget);
  });
}