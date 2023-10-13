using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RepeatedIngredient
{
    public void Enable(GameObject repeatedIngredient)
    {
        repeatedIngredient.SetActive(true);
    }

    public void Unable(GameObject repeatedIngredient)
    {
        repeatedIngredient.SetActive(false);
    }
}

