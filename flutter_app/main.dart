import 'package:flutter/material.dart';

void main() {
  runApp(GartensteuerungApp());
}

class GartensteuerungApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Gartensteuerung',
      theme: ThemeData(
        primarySwatch: Colors.green,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: DashboardScreen(),
    );
  }
}

class DashboardScreen extends StatelessWidget {
  final List<Map<String, dynamic>> zonen = [
    {
      'name': 'Gewächshaus',
      'status': 'Feucht',
      'icon': Icons.local_florist,
      'color': Colors.teal
    },
    {
      'name': 'Feld Links',
      'status': 'Trocken – Gießen nötig',
      'icon': Icons.grass,
      'color': Colors.orange
    },
    {
      'name': 'Feld Rechts',
      'status': 'Feucht',
      'icon': Icons.eco,
      'color': Colors.green
    },
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Gartensteuerung'),
        actions: [
          IconButton(
            icon: Icon(Icons.battery_full),
            onPressed: () {
              ScaffoldMessenger.of(context).showSnackBar(
                SnackBar(content: Text('Akkustand: 89%')),
              );
            },
          )
        ],
      ),
      body: ListView(
        children: [
          ...zonen.map((zone) => Card(
                color: zone['color'].withOpacity(0.1),
                margin: EdgeInsets.all(10),
                child: ListTile(
                  leading: Icon(zone['icon'], color: zone['color']),
                  title: Text(zone['name']),
                  subtitle: Text(zone['status']),
                  trailing: ElevatedButton(
                    onPressed: () {
                      ScaffoldMessenger.of(context).showSnackBar(
                        SnackBar(content: Text('${zone['name']} wird gegossen...')),
                      );
                    },
                    child: Text('Gießen'),
                  ),
                ),
              )),
          SizedBox(height: 20),
          ListTile(
            leading: Icon(Icons.cloud, color: Colors.blueGrey),
            title: Text('Wetterstatus'),
            subtitle: Text('Kein Regen · Kein Frost'),
          ),
        ],
      ),
    );
  }
}
