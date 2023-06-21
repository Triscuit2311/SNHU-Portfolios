 
## CS-360 Portfolio
### Dante Trisciuzzi
### Prof. Jerome DiMarzio

---

## Q&A 


### Briefly summarize the requirements and goals of the app you developed. What user needs was this app designed to address?

I set out to develop an Android app for managing inventory items. I designed the app with individuals, like collectors or small business owners in mind.

### What screens and features were necessary to support user needs and produce a user-centered UI for the app? How did your UI designs keep users in mind? Why were your designs successful?

My UI consisted of a login page, registration page, a main inventory page, a settings page, and severl inventory managing pages (add and modify). I worked to align my designs with the Google developer guidelines to create something that was simple, easy to navigate, and easy on the eyes.

### How did you approach the process of coding your app? What techniques or strategies did you use? How could those be applied in the future?

I worked with recursive task planning, in which I laid out my main goals and determined milestones. Each milestone or feature was then broken down into measurable tasks. This is the basis of how I complete most of my personal software projects, and resembles Agile software development methods. In the future this way of thinking will be essential for solving more complex problems and developing in a large ecosystem.


### How did you test to ensure your code was functional? Why is this process important and what did it reveal?

Most of the testing I performed was functional testing using the Android emulator. Additionally, I used the debugger to find problem areas in my code. I did not use unit testing for this project.

### Considering the full app design and development process, from initial planning to finalization, where did you have to innovate to overcome a challenge?

Well the first problem I had to overcome was; how do I make an inventory app interesting? I chose to make it interesting by seeing how much I could pack into a very simple and useable interface. I faced some other challenges throughout development, like working with the database. I absolutely detest raw SQL queries, but per the guidelines for this project, I needed to use SQL in my code. If I were to solve this my way, I'd use an object based in-memory database in place of the an SQL database.

### In what specific component from your mobile app were you particularly successful in demonstrating your knowledge, skills, and experience?

I think the modify page and it's interaction with the main inventory screen and the database showed a good level of ingenuity. This page allows the user to update the quantity and notes of the items selected from the inventory. I passed variables between fragments, used authentication, validated user inputs, applied some object oriented programming principals to transform objects from database entries to and from a custom data class; as well as applied some Android-specific tricks to make everything feel good and flow correctly.