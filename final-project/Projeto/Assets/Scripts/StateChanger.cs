using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class StateChanger : MonoBehaviour
{

    public void fsm(List<TrackableBehaviour> listOfTrackables) {

        TrackableBehaviour fruit = listOfTrackables[0];
        TrackableBehaviour utens = listOfTrackables[1];
        
        switch (fruit.name)
        {
            case "Banana":
                switch (utens.name)
                {
                    case "Forno":

                        var bananaCake = GameObject.Find("Resultado").transform;

                        bananaCake.Find("BananaCake").gameObject.SetActive(true);

                        break;

                    case "Panela":

                        var bananaJam = GameObject.Find("Resultado").transform;
                        bananaJam.Find("BananaJam").gameObject.SetActive(true);

                        break;

                    case "Espremedor":

                        var bananaJuice = GameObject.Find("Resultado").transform;
                        bananaJuice.Find("BananaJuice").gameObject.SetActive(true);
                        break;
                }
                break;

            case "Pessego":
                switch (utens.name)
                {
                    case "Forno":

                        var peachCake = GameObject.Find("Resultado").transform;

                        peachCake.Find("PeachCake").gameObject.SetActive(true);
                        break;

                    case "Panela":
                        var peachJam = GameObject.Find("Resultado").transform;
                        peachJam.Find("PeachJam").gameObject.SetActive(true);
                        break;

                    case "Espremedor":
                        var peachJuice = GameObject.Find("Resultado").transform;
                        peachJuice.Find("PeachJuice").gameObject.SetActive(true);
                        break;
                }
                break;

            case "Morango":
                switch (utens.name)
                {
                    case "Forno":

                        var strawberryCake = GameObject.Find("Resultado").transform;
                        strawberryCake.Find("StrawberryCake").gameObject.SetActive(true);

                        break;

                    case "Panela":

                        var strawberryJam = GameObject.Find("Resultado").transform;
                        strawberryJam.Find("StrawberryJam").gameObject.SetActive(true);
                        break;

                    case "Espremedor":

                        var strawberryJuice = GameObject.Find("Resultado").transform;
                        strawberryJuice.Find("StrawberryJuice").gameObject.SetActive(true);
                        break;
                }
                break;
        }

    }

    public void unable(List<TrackableBehaviour> listOfTrackables)
    {
        TrackableBehaviour fruit = listOfTrackables[0];
        TrackableBehaviour utens = listOfTrackables[1];

        switch (fruit.name)
        {
            case "Banana":
                switch (utens.name)
                {
                    case "Forno":

                        var bananaCake = GameObject.Find("Resultado").transform;

                        bananaCake.Find("BananaCake").gameObject.SetActive(false);

                        break;

                    case "Panela":

                        var bananaJam = GameObject.Find("Resultado").transform;
                        bananaJam.Find("BananaJam").gameObject.SetActive(false);

                        break;

                    case "Espremedor":

                        var bananaJuice = GameObject.Find("Resultado").transform;
                        bananaJuice.Find("BananaJuice").gameObject.SetActive(false);
                        break;
                }
                break;

            case "Pessego":
                switch (utens.name)
                {
                    case "Forno":

                        var peachCake = GameObject.Find("Resultado").transform;

                        peachCake.Find("PeachCake").gameObject.SetActive(false);
                        break;

                    case "Panela":
                        var peachJam = GameObject.Find("Resultado").transform;
                        peachJam.Find("PeachJam").gameObject.SetActive(false);
                        break;

                    case "Espremedor":
                        var peachJuice = GameObject.Find("Resultado").transform;
                        peachJuice.Find("PeachJuice").gameObject.SetActive(false);
                        break;
                }
                break;

            case "Morango":
                switch (utens.name)
                {
                    case "Forno":

                        var strawberryCake = GameObject.Find("Resultado").transform;
                        strawberryCake.Find("StrawberryCake").gameObject.SetActive(false);

                        break;

                    case "Panela":

                        var strawberryJam = GameObject.Find("Resultado").transform;
                        strawberryJam.Find("StrawberryJam").gameObject.SetActive(false);
                        break;

                    case "Espremedor":

                        var strawberryJuice = GameObject.Find("Resultado").transform;
                        strawberryJuice.Find("StrawberryJuice").gameObject.SetActive(false);
                        break;
                }
                break;
        }

    }

}
