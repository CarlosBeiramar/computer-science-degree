using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OKButton
{
    public void Enable(GameObject okButton)
    {
        okButton.SetActive(true);
    }

    public void Unable(GameObject okButton)
    {
        okButton.SetActive(false);
    }
}
