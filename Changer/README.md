# Changer Challenge <br>
Do Now (Coin Changer)<br>

Create a function called changer that accepts a single argument (a number) and returns an array of numbers as the result.<br>
The function acts as a change machine to translate an amount of money .87cents into the right amount of quarters, dimes, nickles, and pennies.<br>
The function should always return the minimum amount of coins for a given amount of change. Six pennies should be a nickle and a penny, not six pennies.<br>
//Function Type Signature

  changer(1)  == [1]<br>
  changer(2)  == [1, 1]<br>
  changer(5)  == [5]<br>
  changer(25) == [25]<br>
  changer(50) == [25, 25]<br>
  changer(54) == [25, 25, 1, 1, 1, 1]<br>
  changer(99) == [25, 25, 25, 10, 10, 1, 1, 1, 1]<br>
