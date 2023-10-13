import { Space } from "nobox-client";
import { createRowSchema } from "./nobox";


export interface ISoilMoistureRecord {
    id?:string,
    updatedAt?: string,  // Date string
    createdAt?: string,  // Date string
    value: number;
    unit?: string;
}

export const SoilMoistureStructure: Space<ISoilMoistureRecord> = {
    space: "moisturesensor",
    description: "",
    structure: {
        value: {
            description: "Current value",
            type: Number,
            required: true
        },
        unit: {
            description: "Percente or degree",
            required: true,
            type: String,
            defaultValue:'percent'
        }
    }
}

export const SoilStructureModel = createRowSchema<ISoilMoistureRecord>(SoilMoistureStructure);