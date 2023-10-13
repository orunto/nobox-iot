// What is the distance from 1 January 2016

import { formatDistanceToNowStrict } from "date-fns";

// to 1 January 2015, with a suffix?

export function verboseTime(date:Date) {

    const result = formatDistanceToNowStrict(date, {
      addSuffix: true
    });

    return result;
}
//=> 'about 1 year ago'