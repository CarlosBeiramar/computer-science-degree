using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChooseIngredient
{ 
    public void Enable(GameObject chooseIngredient)
    {
        chooseIngredient.SetActive(true);
    }

    public void Unable(GameObject chooseIngredient)
    {
        chooseIngredient.SetActive(false);
    }
}
