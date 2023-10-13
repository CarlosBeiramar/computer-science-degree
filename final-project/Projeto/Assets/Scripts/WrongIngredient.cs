using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WrongIngredient
{
    public void Enable(GameObject wrondIngredient)
    {
        wrondIngredient.SetActive(true);
    }

    public void Unable(GameObject wrondIngredient)
    {
        wrondIngredient.SetActive(false);
    }
}

