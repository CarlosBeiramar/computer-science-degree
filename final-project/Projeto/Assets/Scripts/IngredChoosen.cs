using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IngredChoosen
{
    public void Enable(GameObject ingredChoosen)
    {
        ingredChoosen.SetActive(true);
    }

    public void Unable(GameObject ingredChoosen)
    {
        ingredChoosen.SetActive(false);
    }

}
