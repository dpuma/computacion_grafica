using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotarCubo : MonoBehaviour
{
    // Start is called before the first frame update
    void Start() { }

    public List<GameObject> ListaCubos;

    int[] cubos_X = {0,9,18,3,12,21,6,15,24};
    int[] cubos_Y = {0,1,2,9,10,11,18,19,20};
    int[] cubos_Z = {0,1,2,3,4,5,6,7,8};

    public bool desactivado = true; 

    // Update is called once per frame
    void funcPadres(int[] lista, int aumento, Vector3 axis, float angle, float duration = 1.0f)
    {
        for(int i = 0; i < ListaCubos.Count; i++)
        {
            ListaCubos[i].transform.parent = null; 
        }
        for(int i = 0; i < 9; i++)
        {
            ListaCubos[lista[i] + aumento].transform.parent = transform; 
        }
        StartCoroutine(Rotate(axis, angle, duration));
    }

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Q) && desactivado)
        {
            funcPadres(cubos_X, 0, new Vector3(1,0,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.W) && desactivado)
        {
            funcPadres(cubos_X, 1, new Vector3(1,0,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.E) && desactivado)
        {
            funcPadres(cubos_X, 2, new Vector3(1,0,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.A) && desactivado)
        {
            funcPadres(cubos_X, 0, new Vector3(1,0,0), -90);
        }
        else if(Input.GetKeyDown(KeyCode.S) && desactivado)
        {
            funcPadres(cubos_X, 1, new Vector3(1,0,0), -90);
        }
        else if(Input.GetKeyDown(KeyCode.D) && desactivado)
        {
            funcPadres(cubos_X, 2, new Vector3(1,0,0), -90);
        }
        


        else if(Input.GetKeyDown(KeyCode.R) && desactivado)
        {
            funcPadres(cubos_Y, 0, new Vector3(0,1,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.T) && desactivado)
        {
            funcPadres(cubos_Y, 3, new Vector3(0,1,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.Y) && desactivado)
        {
            funcPadres(cubos_Y, 6, new Vector3(0,1,0), 90);
        }
        else if(Input.GetKeyDown(KeyCode.F) && desactivado)
        {
            funcPadres(cubos_Y, 0, new Vector3(0,1,0), -90);
        }
        else if(Input.GetKeyDown(KeyCode.G) && desactivado)
        {
            funcPadres(cubos_Y, 3, new Vector3(0,1,0), -90);
        }
        else if(Input.GetKeyDown(KeyCode.H) && desactivado)
        {
            funcPadres(cubos_Y, 6, new Vector3(0,1,0), -90);
        }


        else if(Input.GetKeyDown(KeyCode.U) && desactivado)
        {
            funcPadres(cubos_Z, 0, new Vector3(0,0,1), 90);
        }
        else if(Input.GetKeyDown(KeyCode.I) && desactivado)
        {
            funcPadres(cubos_Z, 9, new Vector3(0,0,1), 90);
        }
        else if(Input.GetKeyDown(KeyCode.O) && desactivado)
        {
            funcPadres(cubos_Z, 18, new Vector3(0,0,1), 90);
        }
        else if(Input.GetKeyDown(KeyCode.J) && desactivado)
        {
            funcPadres(cubos_Z, 0, new Vector3(0,0,1), -90);
        }
        else if(Input.GetKeyDown(KeyCode.K) && desactivado)
        {
            funcPadres(cubos_Z, 9, new Vector3(0,0,1), -90);
        }
        else if(Input.GetKeyDown(KeyCode.L) && desactivado)
        {
            funcPadres(cubos_Z, 18, new Vector3(0,0,1), -90);
        }
    }

    IEnumerator Rotate(Vector3 axis, float angle, float duration = 1.0f)
    {
        desactivado = false;

        Quaternion from = transform.rotation; 
        Quaternion to = transform.rotation;
        to *= Quaternion.Euler(axis * angle);

        float elapsed = 0.0f;
        while(elapsed < duration)
        {
            transform.rotation = Quaternion.Slerp(from, to, elapsed / duration);
            elapsed += Time.deltaTime; 
            yield return null; 
        }
        transform.rotation = to; 

        desactivado = true;
    }
}
