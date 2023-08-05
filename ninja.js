import ImportedNinja from "./Ninja.js";
import {compareNinjas} from "./Ninja.js";

const ninja1 = new ImportedNinja("Yoshi");
const ninja2 = new ImportedNinja("Hattori");

assert(ninja1 !== undefined
      && ninja2 !== undefined, "We can create a couple of Ninjas");
assert(!compareNinjas(ninja1, ninja2),
      "We can compare ninjas");
