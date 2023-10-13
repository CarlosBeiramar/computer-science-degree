using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class HowToPlay
{

    public Button menuButton;

    // Update is called once per frame
    void Update()
    {
        menuButton.onClick.AddListener(() => { SceneManager.LoadScene("Main_Menu"); });

    }
}
