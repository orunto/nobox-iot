import { apiUrl, authToken, project } from "@/config/env";

import  {  Config,  getFunctions,  getSchemaCreator  }  from  "nobox-client";

export const config: Config = {
    endpoint:  apiUrl,
    project:  project,
    token: (authToken as string),
};

export const createRowSchema = getSchemaCreator(config, { type: "rowed" });

// export const createKeyGroupSchema = getSchemaCreator(config, { type: "key-group" });

export  const  Nobox  =  getFunctions(config);

