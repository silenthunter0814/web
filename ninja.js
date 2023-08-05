import { message, sayHiToNinja } from "./Ninja.js";

assert(message === "Hello",
      "We can access the imported variable");
assert(sayHiToNinja() === "hello Yoshi",
      "We can say hi to Yoshi from outside the module");
assert(typeof ninja === "undefined",
      "But we cannot access Yoshi directly");
