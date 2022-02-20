google.charts.load('current', {
  'packages': ['bar']
});
google.charts.setOnLoadCallback(drawChart1);
google.charts.load('current', {
  'packages': ['line']
});
var temp = 0;
var salary = [
  ['Язык программирования', 'Junior', 'Middle', 'Senior'],
  ['C', 0, 0, 0],
  ['java', 0, 0, 0],
  ['PHP', 0, 0, 0],
  ['Objective+C', 0, 0, 0],
  ['Ruby', 0, 0, 0],
  ['Python', 0, 0, 0],
  ['JS', 0, 0, 0]
];
var salary_city = "";

function drawChart1() {
  var data = google.visualization.arrayToDataTable(salary);
  //data.setValue(1, 1, 1004);
  var options = {
    chart: {
      title: 'Город',
      subtitle: salary_city,
    },
    chartArea: {
      backgroundColor: {
        fill: '#f8f9fa',
        fillOpacity: 0.1
      },
    },
    backgroundColor: {
      fill: '#f8f9fa',
      fillOpacity: 0.8
    },
  };
  var chart = new google.charts.Bar(document.getElementById('columnchart_material'));
  chart.draw(data, google.charts.Bar.convertOptions(options));
  google.visualization.events.addListener(chart, 'select', selectHandler2);

  function selectHandler2() {
    var selection = chart.getSelection();
    var column = selection[0].column;
    var row = selection[0].row + 1;
    console.log('column: ' + column + 'row: ' + row);
    temp = Number(salary[row][column]);
    console.log(temp);
    google.charts.setOnLoadCallback(drawChart2);
  }
}

function drawChart2() {
  var data = new google.visualization.DataTable();
  data.addColumn('number', 'Month');
  data.addColumn('number', 'Junior');
  //data.addColumn('number', 'Middle');
  //data.addColumn('number', 'Senior');
  data.addRows([
    [1, temp],
    [2, temp * 1.01],
    [3, temp * 1.02],
    [4, temp * 1.03],
    [5, temp * 1.04],
    [6, temp * 1.05],
    [7, temp * 1.008],
    [8, temp * 0.99],
    [9, temp * 0.98],
    [10, temp * 1.05],
    [11, temp * 1.05],
    [12, temp * 1.05],
  ]);
  var options = {
    chart: {
      title: 'Динамика зарплат PHP',
      subtitle: '2020'
    },
    chartArea: {
      backgroundColor: {
        fill: '#f8f9fa',
        fillOpacity: 0.1
      },
    },
    backgroundColor: {
      fill: '#f8f9fa',
      fillOpacity: 0.8
    },
    width: 800,
    height: 500
  };
  var chart = new google.charts.Line(document.getElementById('linechart_material'));
  chart.draw(data, google.charts.Line.convertOptions(options));
}

$(function() {
  $('#select').change(function() {
    let city = $(this).val();
    $.ajax({
      type: "POST",
      url: "http://localhost:8095/getSalary",
      dataType: "text",
      data: {
        city: city
      }
    }).done((msg) => {
      let message = JSON.parse(msg);
      salary_city = city;
      for(let i = 0; i < message.langs.length; i++) {
        if(message.langs[i].name == "C") {
          salary[1][1] = Number(message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0);
          salary[1][2] = Number(message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0);
          salary[1][3] = Number(message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0);
        }
        if(message.langs[i].name == "Java") {
          salary[2][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[2][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[2][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
        if(message.langs[i].name == "PHP") {
          salary[3][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[3][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[3][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
        if(message.langs[i].name == "Objective+C") {
          salary[4][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[4][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[4][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
        if(message.langs[i].name == "Ruby") {
          salary[5][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[5][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[5][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
        if(message.langs[i].name == "Python") {
          salary[6][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[6][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[6][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
        if(message.langs[i].name == "JS") {
          salary[7][1] = message.langs[i].levels.junior != -1 ? message.langs[i].levels.junior : 0;
          salary[7][2] = message.langs[i].levels.middle != -1 ? message.langs[i].levels.middle : 0;
          salary[7][3] = message.langs[i].levels.senior != -1 ? message.langs[i].levels.senior : 0;
        }
      }
      console.log(salary);
      console.log(city);
    })
  });
});