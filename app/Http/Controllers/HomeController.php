<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Contracts\Support\Renderable
     */
    public function index()
    {

        
 
        // Define porta onde arduino está conectado
        $port = "/dev/ttyUSB0";
        // Configura velocidade de comunicação com a porta serial
        exec("stty -F $port raw speed 9600");
        // Inicia comunicação serial
        $fp = fopen($port, 'c+');
        for($i=0;$i<10;$i++){
        $arduino = fgets($fp);
        $arduino_json[$i] = json_decode($arduino);
        }
        
        
        // Escreve na porta
        
        // Fecha a comunicação serial
        fclose($fp);
        

        return view('home', compact("arduino_json"));
    }
}
