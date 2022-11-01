@extends('layouts.app')

@section('content')
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
                <div class="card-header">{{ __('Dashboard') }}</div>

                <div class="card-body">
                    <table class="table">
                        <thead>
                          <tr>
                            <th scope="col">#</th>
                            <th scope="col">Temperatura</th>
                            <th scope="col">Altitude</th>
                            <th scope="col">CO</th>
                            <th scope="col">CO2</th>
                            <th scope="col">Alcohol</th>
                            <th scope="col">NH4</th>
                            <th scope="col">Acetona</th>
                            <th scope="col">AcelX</th>
                            <th scope="col">Acely</th>
                          </tr>
                        </thead>
                        <tbody>
                            @foreach ($arduino_json as $content)

                          <tr>
                            <th scope="row"></th>
                            <td>{{$content->Temperatura}}</td>
                            <td>{{$content->Altitude}}</td>
                            <td>{{$content->CO}}</td>
                            <td>{{$content->CO2}}</td>
                            <td>{{$content->Alcohol}}</td>
                            <td>{{$content->NH4}}</td>
                            <td>{{$content->Acetona}}</td>
                            <td>{{$content->AcelX}}</td>
                            <td>{{$content->AcelY}}</td>
                          </tr>
                         @endforeach
                        </tbody>
                      </table>
                   
                </div>
                
                <div>
                  <canvas id="myChart"></canvas>
                  <script>
                    const labels = [
                      'January',
                      'February',
                      'March',
                      'April',
                      'May',
                      'June',
                    ];
                  
                    const data = {
                      labels: labels,
                      datasets: [{
                        label: 'My First dataset',
                        backgroundColor: 'rgb(255, 99, 132)',
                        borderColor: 'rgb(255, 99, 132)',
                        data: [0, 10, 5, 2, 20, 30, 45],
                      }]
                    };
                  
                    const config = {
                      type: 'line',
                      data: data,
                      options: {}
                    };
                  </script>
                  <script>
                    const myChart = new Chart(
                      document.getElementById('myChart'),
                      config
                    );
                  </script>
                </div>
            </div>
        </div>
    </div>
</div>

@endsection
