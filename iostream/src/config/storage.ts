// Storage configuration

const structures = {
    soilMoistureStructure: {
        "name": "soilMoisture",
        "description": "",
        "slug": "soilMoisture",
        "webhooks": null,
        "recordFieldStructures": [
            {
            "required": false,
            "unique": false,
            "description": "",
            "comment": "",
            "hashed": false,
            "name": "value",
            "slug": "value",
            "type": "NUMBER"
            },
            {
            "required": false,
            "unique": false,
            "description": "",
            "comment": "",
            "hashed": false,
            "name": "unit",
            "slug": "unit",
            "type": "TEXT"
            }
        ]
    }
}

const sensors = [
    {
        name: "Capacity soil moisture sensor",
        metric: "Soil Moisture",
        slug:'soilMiosture',
        unit: "percent",
        structure: structures.soilMoistureStructure,
        record: {
            query: "/soilmoisture",
            // write: ""
        }
    },
    {
        name: "",
        metric: "Humidity",
        slug:'humidity',
        unit: "percent",
        record: {
            query: null,
            // write: null
        }
    },
    {
        name: "",
        metric: "Temperature",
        slug:'temperature',
        unit: "degree",
        record: {
            query: null,
            // write: null
        }
    }
]


const devices = [
    {
        name: "Tensilica L106 32-bit microcontroller",
        type: "Esp8266"
    }
]


export {
    sensors,
    devices,
}