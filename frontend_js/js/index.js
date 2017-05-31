var nodes = new vis.DataSet([]);
var edges = new vis.DataSet([]);

// create a network
var container = document.getElementById('tspgraph');
var data = {
  nodes: nodes,
  edges: edges
};
var options = {
  physics: {stabilization: true, solver: 'forceAtlas2Based'}
};
var network = new vis.Network(container, data, options);

function addNode() {
  addNodeToTable();
  updateGraphFromTable();
}

function removeNode() {
  removeNodeFromTable();
  updateGraphFromTable();
}

function removeNodeFromTable() {
  let nodesTab = document.getElementById("nodesTab");
  let nodeNames = nodesTab.getElementsByTagName("thead")[0].getElementsByTagName("tr")[0];
  let nodeValues = nodesTab.getElementsByTagName("tbody")[0];
  let nodeSize = nodeValues.getElementsByTagName("tr").length;
  let existingNodes = nodeValues.getElementsByTagName("tr");

  nodeNames.getElementsByTagName("td")[nodeNames.getElementsByTagName("td").length - 1].remove();

  for(let i = 0; i < nodeSize - 1; i++) {
    existingNodes[i].getElementsByTagName("td")[nodeSize - 1].remove();
  }

  existingNodes[nodeSize - 1].remove();
}

function addNodeToTable() {
  let nodesTab = document.getElementById("nodesTab");
  let nodeNames = nodesTab.getElementsByTagName("thead")[0].getElementsByTagName("tr")[0];
  let nodeValues = nodesTab.getElementsByTagName("tbody")[0];
  let nodeSize = nodeValues.getElementsByTagName("tr").length;
  let existingNodes = nodeValues.getElementsByTagName("tr");
  let td = document.createElement("td");
  td.innerHTML = "<input type='text' class='form-control' value='test" + nodeSize + "'></input>";
  nodeNames.appendChild(td);

  for(let i = 0; i < nodeSize; i++) {
    let td = document.createElement("td");
    existingNodes[i].appendChild(td);
  }
  let tr = document.createElement("tr");
  for(let i = 0; i < (nodeSize + 1); i++) {
    let td = document.createElement("td");
    if(i === nodeSize) {
      td.innerHTML = "<input class='form-control' type='number' value='0' disabled> </input>";
    } else {
      td.innerHTML = "<input class='form-control' type='number' value='100'> </input>";
    }
    tr.appendChild(td);
  }
  nodeValues.appendChild(tr);
}

function updateGraphFromTable() {
  let nodesTab = document.getElementById("nodesTab");
  let nodeNames = nodesTab.getElementsByTagName("thead")[0].getElementsByTagName("tr")[0].getElementsByTagName("td");
  for(let i = 0; i < nodeNames.length; i++) {
      nodes.update({id: (i + 1), label: nodeNames[i].getElementsByTagName("input")[0].value});
  }
  if(nodes.length > nodeNames.length) {
    let nodesLength = nodes.length;
    for(let i = nodeNames.length; i < nodesLength; i++) {
      nodes.remove(i + 1);
    }
  }
  edges.clear();
  let nodeValuesRows = nodesTab.getElementsByTagName("tbody")[0].getElementsByTagName("tr");
  for(let i = 0; i < nodeValuesRows.length; i++) {
    let nodeValues = nodeValuesRows[i].getElementsByTagName("td");
    for(let j = 0; j < nodeValues.length; j++) {
      if(i!==j && nodeValues[j].hasChildNodes()) {
        edges.add({from: i + 1, to: j + 1, label: nodeValues[j].getElementsByTagName("input")[0].value, length: nodeValues[j].getElementsByTagName("input")[0].value})
      }
    }
  }
  let jsonObj = { nodes : nodes.get({fields: ['id', 'label']}), edges : edges.get({fields: ['from', 'to', 'length']}) };
  console.log(JSON.stringify(jsonObj));
}

function handleFiles(files) {
  let file = files[0];
  let reader = new FileReader();

  nodes.clear();
  edges.clear();

  reader.onload = function(event) {
    let text = event.target.result;
    let textLines = text.split(/\r?\n/);
    for(let i = 0; i < textLines.length; i++) {
      let lineValues = textLines[i].split(" ");
      for(let j = 0; j < lineValues.length; j++) {
        if(i === 0) {
          nodes.add({id: (j + 1), label: lineValues[j]});
        } else if(lineValues[j] !== "0" && lineValues[j] !== "") {
          edges.add({from: j + 1, to: i, label: lineValues[j], length: lineValues[j]});
        }
      }
    }
  }

  reader.readAsText(file);
}


function farthestInsertionTsp() {
  //1
  let newNodes = new vis.DataSet([]);
  let newEdges = new vis.DataSet([]);
  let firstNode = nodes.get(Math.floor((Math.random() * nodes.length) + 1));
  newNodes.add(firstNode);
  //2
  if(nodes.length > 1) {
    let edgesConnectedToNode = edges.get({
      filter: function (item) {
        return (item.from === firstNode.id || item.to === firstNode.id);
      }
    });
    let edgesConnectedDataSet = new vis.DataSet([]);
    edgesConnectedDataSet.add(edgesConnectedToNode);
    let maxEdge = edgesConnectedDataSet.max('length');
    let addedNode;
    if(maxEdge.from === firstNode.id) {
      addedNode = nodes.get(maxEdge.to);
    } else {
      addedNode = nodes.get(maxEdge.from);
    }
    newNodes.add(addedNode);
    newEdges.add({from: firstNode.id, to: addedNode.id, label: maxEdge.label, length: maxEdge.length});
    newEdges.add({from: addedNode.id, to: firstNode.id, label: maxEdge.label, length: maxEdge.length});
  }
  while(newNodes.length < nodes.length) {
    //3
    var farthestDistance = Number.MIN_VALUE;
    let maxDistNodeId;
    let edgesToCheck = edges.get({
      filter: function (item) {
        return ((newNodes.getIds().includes(item.from) && !newNodes.getIds().includes(item.to)) ||
        (!newNodes.getIds().includes(item.from) && newNodes.getIds().includes(item.to)));
      }
    });
    for(let i = 0; i < edgesToCheck.length; i++) {
      if(parseFloat(edgesToCheck[i].length) > parseFloat(farthestDistance)) {
        farthestDistance = edgesToCheck[i].length;
        if(newNodes.getIds().includes(edgesToCheck[i].from)) {
          maxDistNodeId = edgesToCheck[i].to;
        }
        if(newNodes.getIds().includes(edgesToCheck[i].to)) {
          maxDistNodeId = edgesToCheck[i].from;
        }
      }
    }
    let maxDistNode = nodes.get(maxDistNodeId);

    //4
    let lowestCost = Number.MAX_VALUE;
    let edgeToRemove;
    let firstEdgeToAdd;
    let secondEdgeToAdd;

    let edgesInNewEdges = newEdges.get();

    for(let i = 0; i < edgesInNewEdges.length; i++) {
      let edgeInGraph = edgesInNewEdges[i];
      let edgeFarthestFrom;
      let edgeFarthestTo;
      for(let j = 0; j < edgesToCheck.length; j++) {
        if((edgesToCheck[j].from === maxDistNode.id && edgesToCheck[j].to === edgeInGraph.from) ||
           (edgesToCheck[j].from === edgeInGraph.from && edgesToCheck[j].to === maxDistNode.id)) {
          edgeFarthestFrom = edgesToCheck[j];
        }
        if((edgesToCheck[j].from === maxDistNode.id && edgesToCheck[j].to === edgeInGraph.to) ||
           (edgesToCheck[j].from === edgeInGraph.to && edgesToCheck[j].to === maxDistNode.id)) {
          edgeFarthestTo = edgesToCheck[j];
        }
      }
      if(edgeFarthestFrom !== undefined && edgeFarthestTo !== undefined) {
        if((parseFloat(edgeFarthestFrom.length) + parseFloat(edgeFarthestTo.length) - parseFloat(edgeInGraph.length)) < lowestCost) {
          lowestCost = parseFloat(edgeFarthestFrom.length) + parseFloat(edgeFarthestTo.length) - parseFloat(edgeInGraph.length);
          edgeToRemove = edgeInGraph;
          firstEdgeToAdd = edgeFarthestFrom;
          secondEdgeToAdd = edgeFarthestTo;
        }
      }
    }
    newNodes.add(maxDistNode);
    newEdges.remove(edgeToRemove);
    newEdges.add(firstEdgeToAdd);
    newEdges.add(secondEdgeToAdd);

  }
  edges.clear();
  edges.add(newEdges.get());
}
