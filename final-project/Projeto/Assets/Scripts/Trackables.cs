using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using Vuforia;
using UnityEngine.UI;
using UnityEngine.SceneManagement;



public class Trackables : MonoBehaviour
{
    // Lista para os trackables feitos.
    List<TrackableBehaviour> listOfActiveTrackables = new List<TrackableBehaviour>();

    // Lista com o nome de todas as frutas
    List<string> frutas = new List<string> { "Banana", "Morango", "Pessego" };

    // Lista com o nome de todos utensilios
    List<string> utensilios = new List<string> { "Forno", "Espremedor", "Panela" };

    // Lista com o nome de todos os ingredientes
    List<string> ingredientes = new List<string> { "Agua", "Ovo", "Farinha", "Acucar" };

    Dictionary<string, List<string>> receitas = new Dictionary<string, List<string>>()
    {
        {"Forno", new List<string> { "Acucar", "Farinha" } },
        {"Espremedor", new List<string> { "Agua", "Acucar" } },
        {"Panela", new List<string> { "Agua", "Ovo" } }
    };


    // canvas para indicar que o primeiro target tem que ser fruta
    public GameObject fruitFirst;

    // canvas para dar erro quando são escolhidos mais do que um target
    public GameObject errotrackables;
    // canvas para indicar que o segundo target tem que ser utensilio.
    public GameObject utenSecond;
    // objeto do botão ok.
    public GameObject objectOkButton;

    // canvas para indicar que o ingrediente não está correto.
    public GameObject wrongIngredient;


    // canvas para indicar que o ingrediente já foi escolhido.
    public GameObject repeatedIngredient;

    // canvas para inserir um ingrediente
    public GameObject chooseIngredient;

    public GameObject selectFruit;

    public GameObject selectUten;

    public GameObject receitaTerm;

    public Button okbutton;
    public Button exitbutton;
    public Button novareceitaButton;


    OKButton ok = new OKButton();
    FruitFirst f = new FruitFirst();
    UtenSecond u = new UtenSecond();
    ErroTrackables erTra = new ErroTrackables();
    RepeatedIngredient rpIngre = new RepeatedIngredient();
    WrongIngredient wrongIngre = new WrongIngredient();
    ChooseIngredient chooseIngre = new ChooseIngredient();
    ChooseFruit chooseFruit = new ChooseFruit();
    UtenChoosen chooseUten = new UtenChoosen();
    ReceitaConcl receitaConcl = new ReceitaConcl();

    // maquina de estados para definir o comportamento após os targets lidos.
    StateChanger st = new StateChanger();
    
    int ntrackables = 0;
    bool okclicked = false;
    bool frutachoosen = false;
    bool utenChoosen = false;
    

    private void Update()
    {

        /*
         * Get the Vuforia StateManager
         * This class is used to manage the state of all TrackableBehaviours,
         * create them, associate them with Trackables, update their pose
         */
        StateManager sm = TrackerManager.Instance.GetStateManager();

        // Query the StateManager to retrieve the list of
        // currently 'active' trackables 
        //(i.e. the ones currently being tracked by Vuforia)
        IEnumerable<TrackableBehaviour> activeTrackables = sm.GetActiveTrackableBehaviours();

        exitButtonClicked();

        if (!frutachoosen)
        {
            chooseFruit.Enable(selectFruit);
        }

        // verifica quantos targets leu.
        if (checkTrackableQtf(activeTrackables))
        {
            //caso tenha lido vários targets faz desaparecer o canvas.
            erTra.Unable(errotrackables);

            //só entra neste if se o número de targets lidos é < 2
            if (ntrackables < 5)
            {
                foreach (TrackableBehaviour tb in activeTrackables)
                {

                    // verifica se o primeiro target é fruta.
                    if (checkTrackableFruit(tb) && ntrackables == 0)
                    {
                        listOfActiveTrackables.Add(tb);
                        f.Unable(fruitFirst);
                        ntrackables++;
                        frutachoosen = true;
                        chooseFruit.Unable(selectFruit);
                        ok.Enable(objectOkButton);
                        okbutton.onClick.AddListener(() => { okclicked = true; ok.Unable(objectOkButton); });
                    }

                    // se nao for uma fruta e tiver que ser uma fruta a ser escolhida.
                    else if (!checkTrackableFruit(tb) && ntrackables == 0)
                    {
                        f.Enable(fruitFirst);
                    }

                    if (!utenChoosen && ntrackables == 1)
                    {
                        chooseUten.Enable(selectUten);

                        // verifica se o segundo target é utensilio
                        if (checkTrackableUtens(tb) && ntrackables == 1 && okclicked)
                        {
                            utenChoosen = true;
                            chooseUten.Unable(selectUten);
                            okclicked = false;
                            listOfActiveTrackables.Add(tb);
                            u.Unable(utenSecond);
                            ntrackables++;
                            ok.Enable(objectOkButton);
                            okbutton.onClick.AddListener(() => { okclicked = true; ok.Unable(objectOkButton); });
                        }
                        else if (!checkTrackableUtens(tb) && ntrackables == 1 && okclicked)
                        {
                            u.Enable(utenSecond);
                        }
                    }
                    // verifica se é ingrediente
                    else if (checkTrackableIngredientes(tb) && (ntrackables == 2 || ntrackables == 3) && okclicked)
                    {
                        string utensilio = listOfActiveTrackables[1].name;
                        rpIngre.Unable(repeatedIngredient);
                        wrongIngre.Unable(wrongIngredient);
                        chooseIngre.Unable(chooseIngredient);

                        if (receitas[utensilio].Contains(tb.name) && !listOfActiveTrackables.Contains(tb))
                        {
                            okclicked = false;
                            ntrackables++;
                            ok.Enable(objectOkButton);
                            listOfActiveTrackables.Add(tb);
                            okbutton.onClick.AddListener(() => { okclicked = true; ok.Unable(objectOkButton); });

                        }
                        else if (listOfActiveTrackables.Contains(tb))
                        {
                            rpIngre.Enable(repeatedIngredient);
                        }
                        else if (!receitas[utensilio].Contains(tb.name))
                        {
                            wrongIngre.Enable(wrongIngredient);
                        }
                    }else if (!checkTrackableIngredientes(tb) && (ntrackables == 2 || ntrackables == 3) && okclicked)
                    {
                        chooseIngre.Enable(chooseIngredient);
                    }
                    else if (tb.name == "Resultado" && ntrackables == 4 && okclicked)
                    {
                        ntrackables++;
                    }
                }
            }
        }
        else
        {
            ok.Unable(objectOkButton);
            erTra.Enable(errotrackables);
        }


        if(ntrackables == 5)
        {
            st.fsm(listOfActiveTrackables);
            receitaConcl.Enable(receitaTerm);
            novareceitaButton.onClick.AddListener(() => {
                receitaConcl.Unable(receitaTerm);
                ntrackables = 0;
                okclicked = false;
                frutachoosen = false;
                utenChoosen = false;
                st.unable(listOfActiveTrackables);
                listOfActiveTrackables.Clear();
            });
        }



    }

    private void exitButtonClicked()
    {
        exitbutton.onClick.AddListener(() => { SceneManager.LoadScene("Main_Menu"); });
    }

    private bool checkTrackableQtf(IEnumerable<TrackableBehaviour> activeTrackables)
    {

        if (activeTrackables.Count() > 1)
        {
            return false;
        }
        return true;
    }

    private bool checkTrackableFruit(TrackableBehaviour tb)
    {
        if (frutas.Contains(tb.name)){
            return true;
        }
        return false;
    }

    private bool checkTrackableIngredientes(TrackableBehaviour tb)
    {
        if (ingredientes.Contains(tb.name))
        {
            return true;
        }
        return false;
    }


    private bool checkTrackableUtens(TrackableBehaviour tb)
    {
        if (utensilios.Contains(tb.name))
        {
            return true;
        }
        return false;
    }

}
