'use client';
import { SoilStructureModel } from '@/config/structures';
// Sensor context
import { ISoilMoisture } from '@/config/types';
import {createContext, useContext,useState, useEffect, ReactNode} from 'react';

type Status = 'loading' | 'not-loading';
interface ISensorStateContext {
    records: ISoilMoisture[],
    status: Status,
    updateStatus?: (load:boolean)=>void
}

interface ISensorContextProvider {
    children: ReactNode
}




// ===========================================================
const initialState:ISensorStateContext = {
    status: 'not-loading',
    records: []
}




const SensorContext = createContext<ISensorStateContext>(initialState);
const useSensorContext = ()=>useContext(SensorContext);

export default useSensorContext;



export const SensorContextProvider = (props:ISensorContextProvider) => {

    const [records, setRecords] = useState<ISoilMoisture[]>([]);
    const [status, setStatus] = useState<Status>('loading');


    const loadRecords = async () => {
        
        if(status !== 'loading') return;
        
        const records = await SoilStructureModel.find({})

        // return records; 
        setStatus(()=>'not-loading')
        setRecords(()=>Array.isArray(records) ? [...records].reverse() : []);
    }


    useEffect(()=>{
        (
            ()=>loadRecords()
        )()
    // eslint-disable-next-line react-hooks/exhaustive-deps
    }, [status, records]);


    const context:ISensorStateContext = {
        records,
        status,

        updateStatus: (load)=>setStatus(()=>load ? 'loading' : 'not-loading')
    }

    return (
        <SensorContext.Provider value={context}>

            <SensorContext.Consumer>
                {
                    ()=>props.children
                }
            </SensorContext.Consumer>

            {/* {props.children} */}
        </SensorContext.Provider>
    )
}
