using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Main : MonoBehaviour
{

    public Button newGame;
    public Button how_to_play;
    public Button quit;
    public AudioSource initSound;

    public void Update()
    { 
        newGame.onClick.AddListener(() => { SceneManager.LoadScene("SampleScene"); });
        how_to_play.onClick.AddListener(() => { SceneManager.LoadScene("How_to_play"); });
        quit.onClick.AddListener(() => { Application.Quit();});
    }

    public void Start()
    {
        initSound.Play();
    }
}
