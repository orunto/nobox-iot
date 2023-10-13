type Unit = 'percent' | 'degree' | string;


export interface ISoilMoisture {
    id: string,
    updatedAt: string,  // Date string
    createdAt: string,  // Date string
    value: number,
    unit?: Unit
}