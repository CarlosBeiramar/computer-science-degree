using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChooseFruit
{
    public void Enable(GameObject chooseFruit)
    {
        chooseFruit.SetActive(true);
    }

    public void Unable(GameObject chooseFruit)
    {
        chooseFruit.SetActive(false);
    }
}
