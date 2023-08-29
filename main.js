var url = 'https://jsonplaceholder.typicode.com/users';
var author = {
    name: 'Hero',
    email: 'hero@example.com'
};
var request = new Request(url, {
    method: 'POST',
    body: JSON.stringify(author),
    headers: new Headers({
        'Content-Type': 'application/json; charset=UTF-8'
    })
});

fetch(request)
    .then(response => {
        return response.json();
    })
    .then(data => {
        console.log(JSON.stringify(data));
    })
    .catch(error => {
        console.log(error);
    });
// Output: {name: 'Hero', email: 'hero@example.com', id: 11}