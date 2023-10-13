import { ISoilMoistureRecord } from "@/config/structures";

interface MetricProps {
    logs: ISoilMoistureRecord[]
}

const Metric = (props:MetricProps) => {
    const logs = props.logs;
    const recent_log = logs.length >= 1 ? logs[0] : null;

    return (
        <span className='text-grand text-lg2 d-block text-bold'>
            {
                !recent_log ? '--' : (
                    <>
                        {recent_log.value} %
                    </>
                )
            }
            {/* <sup>o</sup>C */}
        </span>
    )
}


export default Metric;