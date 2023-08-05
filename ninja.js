const MouseCounterModule = function() {
    let numClicks = 0;
    const handleClick = () => {
        alert(++numClicks);
    };

    return {
        countClicks: () => {
            document.addEventListener("click", handleClick);
        }
    };
}();

(function(module) {
    let numScrolls = 0;
    const handleScroll = () => {
        alert(++numScrolls);
    }

    module.countScrolls = () => {
        document.addEventListener("wheel", handleScroll);
    };
})(MouseCounterModule);


import { message, sayHiToNinja } from "Ninja.js";

assert(message === "Hello",
      "We can access the imported variable");
assert(sayHiToNinja() === "hello Yoshi",
      "We can say hi to Yoshi from outside the module");
assert(typeof ninja === "undefined",
      "But we cannot access Yoshi directly");