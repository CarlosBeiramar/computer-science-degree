using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Class usada para ativar o aviso a dizer que o segundo target tem que
// ser um utensilio

public class ErroTrackables
{
    public void Enable(GameObject erroTrackable)
    {
        erroTrackable.SetActive(true);
    }

    public void Unable(GameObject erroTrackable)
    {
        erroTrackable.SetActive(false);
    }
}
