using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UtenChoosen
{
    public void Enable(GameObject utenChoosen)
    {
        utenChoosen.SetActive(true);
    }

    public void Unable(GameObject utenChoosen)
    {
        utenChoosen.SetActive(false);
    }
}
