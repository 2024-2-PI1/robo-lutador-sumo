import React, { useState } from 'react';
import './App.css';
import {
  BarChart,
  Bar,
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  Legend,
  CartesianGrid,
  ResponsiveContainer,
  ScatterChart,
  Scatter,
  AreaChart,
  Area,
} from 'recharts';

const initialData = [
  {
    test: '1',
    expectedTime: 40,
    realTime: 80,
    expectedDistance: 800,
    realDistance: 800,
    lineDetection: 0,
  },
  {
    test: '2',
    expectedTime: 99,
    realTime: 116,
    expectedDistance: 83,
    realDistance: 83,
    lineDetection: 0,
  },
  {
    test: '3',
    expectedTime: 3,
    realTime: 180,
    expectedDistance: null,
    realDistance: null,
    lineDetection: 0,
  },
  {
    test: '4',
    expectedTime: 10,
    realTime: 120,
    expectedDistance: 93,
    realDistance: 93,
    lineDetection: 0,
  },
  {
    test: '5',
    expectedTime: 5,
    realTime: 180,
    expectedDistance: 103,
    realDistance: 103,
    lineDetection: 0,
  },
  {
    test: '6',
    expectedTime: 4,
    realTime: 240,
    expectedDistance: 61,
    realDistance: 61,
    lineDetection: 1,
  },
  {
    test: '7',
    expectedTime: null,
    realTime: null,
    expectedDistance: 41,
    realDistance: 83,
    lineDetection: 0,
  },
  {
    test: '8',
    expectedTime: null,
    realTime: null,
    expectedDistance: 21,
    realDistance: 78,
    lineDetection: 0,
  },
  {
    test: '9',
    expectedTime: null,
    realTime: null,
    expectedDistance: 2,
    realDistance: 2,
    lineDetection: 0,
  },
  {
    test: '10',
    expectedTime: null,
    realTime: null,
    expectedDistance: 21,
    realDistance: 21,
    lineDetection: 0,
  },
];

const Dashboard = () => {
  const [data, setData] = useState(initialData);
  const [newExpectedTime, setNewExpectedTime] = useState(0);
  const [newRealTime, setNewRealTime] = useState(0);
  const [newExpectedDistance, setNewExpectedDistance] = useState(0);
  const [newRealDistance, setNewRealDistance] = useState(0);
  const [newLineDetection, setNewLineDetection] = useState(0);

  const addNewTest = () => {
    const newTestNumber = (data.length + 1).toString();
    const newTest = {
      test: newTestNumber,
      expectedTime: newExpectedTime,
      realTime: newRealTime,
      expectedDistance: newExpectedDistance,
      realDistance: newRealDistance,
      lineDetection: newLineDetection,
    };
    setData([...data, newTest]);

    setNewExpectedTime(0);
    setNewRealTime(0);
    setNewExpectedDistance(0);
    setNewRealDistance(0);
    setNewLineDetection(0);
  };

  const executionData = [];

  let state = 'rotating';
  let stateTime = 0;
  let currentDistance = null;

  for (let i = 0; i < 100; i++) {
    let motorSpeed = 0;
    let perceivedDistance = 200;
    let lineDetected = 0;

    switch (state) {
      case 'rotating':
        motorSpeed = 0;
        perceivedDistance = 200;

        if (stateTime >= 3) {
          state = 'approaching';
          stateTime = 0;
          currentDistance = 140;
        }
        break;

      case 'approaching':
        if (currentDistance > 10) {
          motorSpeed = 100;
          perceivedDistance = currentDistance;

          currentDistance -= 40;

          if (currentDistance <= 10) {
            motorSpeed = 255;
            perceivedDistance = 10;
            state = 'pushing';
            stateTime = 0;
          }
        }
        break;

      case 'pushing':
        if (stateTime < 2) {
          motorSpeed = 255;
          perceivedDistance = 5;
        } else {
          motorSpeed = 0;
          lineDetected = 1;
          state = 'reversing';
          stateTime = 0;
        }
        break;

      case 'reversing':
        motorSpeed = -100;
        perceivedDistance = 200;

        if (stateTime >= 2) {
          state = 'rotating';
          stateTime = 0;
        }
        break;

      default:
        break;
    }

    executionData.push({
      time: i,
      motorSpeed,
      perceivedDistance,
      lineDetected,
    });
    stateTime++;
  }

  return (
    <div className="p-6">
      <h1 className="text-2xl font-bold mb-4">
        Experimento do Robô - Dashboard
      </h1>

      <div className="mb-6 gap-4 flex flex-row">
        <input
          type="number"
          className="p-2 rounded-md border-2 border-gray-300"
          placeholder="Tempo esperado"
          onChange={(e) => setNewExpectedTime(Number(e.target.value))}
        />
        <input
          type="number"
          className="p-2 rounded-md border-2 border-gray-300"
          placeholder="Tempo real"
          onChange={(e) => setNewRealTime(Number(e.target.value))}
        />
        <input
          type="number"
          className="p-2 rounded-md border-2 border-gray-300"
          placeholder="Distância esperada"
          onChange={(e) => setNewExpectedDistance(Number(e.target.value))}
        />
        <input
          type="number"
          className="p-2 rounded-md border-2 border-gray-300"
          placeholder="Distância real"
          onChange={(e) => setNewRealDistance(Number(e.target.value))}
        />
        <input
          type="number"
          className="p-2 rounded-md border-2 border-gray-300"
          placeholder="Detecção da linha"
          onChange={(e) => setNewLineDetection(Number(e.target.value))}
        />
        <button
          className="p-2 rounded-md bg-blue-500 text-white"
          onClick={addNewTest}
        >
          Adicionar Teste
        </button>
      </div>

      {/* Gráfico de Barras - Tempo de Funcionamento */}
      <div className="mb-6">
        <h2 className="text-xl font-semibold mb-2">Tempo de Funcionamento</h2>
        <ResponsiveContainer width="100%" height={300}>
          <BarChart data={data}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis
              dataKey="test"
              label={{ value: 'Teste', position: 'insideBottom', offset: -5 }}
            />
            <YAxis
              label={{ value: 'Segundos', angle: -90, position: 'insideLeft' }}
            />
            <Tooltip />
            <Legend />
            <Bar dataKey="expectedTime" fill="#8884d8" name="Esperado" />
            <Bar dataKey="realTime" fill="#82ca9d" name="Real" />
          </BarChart>
        </ResponsiveContainer>
      </div>

      {/* Gráfico de Linhas - Distância Máxima Percebida */}
      <div className="mb-6">
        <h2 className="text-xl font-semibold mb-2">
          Distância Máxima Percebida
        </h2>
        <ResponsiveContainer width="100%" height={300}>
          <LineChart data={data}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis
              dataKey="test"
              label={{ value: 'Teste', position: 'insideBottom', offset: -5 }}
            />
            <YAxis
              label={{ value: 'cm', angle: -90, position: 'insideLeft' }}
            />
            <Tooltip />
            <Legend />
            <Line
              type="monotone"
              dataKey="expectedDistance"
              stroke="#8884d8"
              name="Esperado"
            />
            <Line
              type="monotone"
              dataKey="realDistance"
              stroke="#82ca9d"
              name="Real"
            />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* Gráfico de Dispersão - Detecção da Linha Preta */}
      <div className="mb-6">
        <h2 className="text-xl font-semibold mb-2">Detecção da Linha Preta</h2>
        <ResponsiveContainer width="100%" height={300}>
          <ScatterChart>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis
              dataKey="test"
              label={{ value: 'Teste', position: 'insideBottom', offset: -5 }}
            />
            <YAxis
              label={{ value: 'Detecção', angle: -90, position: 'insideLeft' }}
              domain={[0, 'dataMax']}
              allowDecimals={false}
            />
            <Tooltip />
            <Legend />
            <Scatter
              name="Detecção"
              data={data}
              fill="#ff7300"
              dataKey="lineDetection"
            />
          </ScatterChart>
        </ResponsiveContainer>
      </div>
      {/* Gráfico de Execução */}
      <div className="mb-6">
        <h2 className="text-xl font-semibold mb-2">Execução do Robô</h2>
        <ResponsiveContainer width="100%" height={300}>
          <AreaChart data={executionData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis
              dataKey="time"
              label={{
                value: 'Tempo (s)',
                position: 'insideBottom',
                offset: -5,
              }}
            />
            <YAxis
              label={{ value: 'Valores', angle: -90, position: 'insideLeft' }}
            />
            <Tooltip />
            <Legend />
            <Area
              type="monotone"
              dataKey="motorSpeed"
              stroke="#8884d8"
              fill="#8884d8"
              name="Velocidade do Motor"
            />
            <Area
              type="monotone"
              dataKey="perceivedDistance"
              stroke="#82ca9d"
              fill="#82ca9d"
              name="Distância Percebida"
            />
            <Scatter
              name="Linha Detectada"
              data={executionData}
              dataKey="lineDetected"
              fill="#ff7300"
              shape="circle"
            />
          </AreaChart>
        </ResponsiveContainer>
      </div>
    </div>
  );
};

export default Dashboard;
