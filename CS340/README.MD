
## CS-340 Portfolio
### Dante Trisciuzzi
### Prof. Jeff Sanford

---

## Q&A 

---
### How do you write programs that are maintainable, readable, and adaptable? Especially consider your work on the CRUD Python module from Project One, which you used to connect the dashboard widgets to the database in Project Two. What were the advantages of working in this way? How else could you use this CRUD Python module in the future?

The key to writeing re-usable modules such as the CRUD module I developed for Project One is modularity. Instead of writing a module specifically for accessing the animal shelter's database documents, I wrote a generalized abstraction over the PyMongo functionality needed to access any MongoDB database. This means in the future I can re-use this module to work with any database.


---
### How do you approach a problem as a computer scientist? Consider how you approached the database or dashboard requirements that Grazioso Salvare requested. How did your approach to this project differ from previous assignments in other courses? What techniques or strategies would you use in the future to create databases to meet other client requests?

I approach solving these problems in a somewhat recursive manner. This is to say that I start with a general idea of the goal, then break it down into smaller goals, which get broken down into tasks, sub-tasks, etc. This approach works well for computer science related tasks more than for other academic tasks I have tackled in the past. Computer science works in absolutes, whereas other topics can be far more subjective. In the future I would take a similar approach, though I might rely on proven libraries for managing MongoDB databases since there are many security vectors that need to be covered.

---
### What do computer scientists do, and why does it matter? How would your work on this type of project help a company, like Grazioso Salvare, to do their work better?

Computer scientists solve problems; there is no limit to the ways a software engineer or data scientist can help a company. In the case of an animal shelter, having all the data on the animals available when needed makes every aspect of caring for the animals faster. Consider ordering supplies or food, or setting up adoption meetings for thousands of animals without having access to data in a computer system. Doing this by hand would cost a lot of time (and money).