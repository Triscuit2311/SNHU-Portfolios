# CS210-M2-Clocks
A 12-Hour and 24-hour clock application with H/M/S increments.

## Module eight response: 
- Summarize the project and what problem it was solving.
> This application displays two clocks, a 12-hour and 24-hour clock. While ticking, the user may increase the hours, minutes, or seconds. This application displays two clocks, a 12-hour and 24-hour clock. While ticking, the user may increase the hours, minutes, or seconds. 
- What did you do particularly well?
> The way I designed the ticking/refresh mechanism, I feel is quite clever. Rather than clearing the screen, I used ANSI escape sequences to reposition the cursor and overwrite the times. This makes for a smooth-operating program, and allows the user to have very responsive inputs.
- Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
> My code is overcomplicated. I could have condensed the clock structure (That contains the clock data) and the clock display structure (that renders the clock and does user I/O) into a single class.
- Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
> The biggest challenge for this project was designing the user I/O system, since I really wanted responsive inputs and did not want the user to need to confirm their inputs. In order to make this work I used some C tricks to take a single character from the input stream. Though this require a good deal of error handling, it worked out for the best.
- What skills from this project will be particularly transferable to other projects or course work?
> I learned a lot about program design while working on this application, particularly revising the program flow as I work and discover correctable errors.
- How did you make this program maintainable, readable, and adaptable?
> By keeping my code (perhaps overly) modular and providing comments, it would be simple for a programmer to add more clocks to my program, change the display mechanism, or even take the core components to another project. By creating a githup repo, I'm able to document my changes, this also helps for maintainability since in the case of an error, we can trace the mistake.
