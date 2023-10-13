import Image from "next/image";


type IconProps = {
    name: string,
    animation?:'rotate' | string,
    title?:string,
    link?: string,
    action?: Function
}


const Icon = (props:IconProps) => {

    const image = <Image
                    src={`/images/icons/${props.name}.svg`}
                    alt="icon"
                    width={80}
                    height={80}
                />
    
    if (props.link) {
        return (
            <a
                href={props.link || '#'}
                className='icon'
                data-animation={props.animation || ''}
                title={props.title}
                
            >
                {image}
            </a>
        )
    }


    return (
        <button
            className='icon'
            data-animation={props.animation || ''}
            title={props.title}
            onClick={()=> props.action && props.action()}
        >
            {image}
        </button>
    )
}


export default Icon;