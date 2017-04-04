//
//  brush.h
//  Brush
//
//  Created by alp tugan on 03/04/17.
//
//

#ifndef brush_h
#define brush_h

#include "ofMain.h"
#include "ofxGui.h"

class brush {
public:
    vector<vector<ofVec2f>> points;
    
    
    ofVec3f thisPoint;
    ofVec3f nextPoint;
    
    ofVec3f leftPoint;
    ofVec3f rightPoint;
    
    bool isActive;
    vector<int> nthStroke;
    
    ofxPanel gui;
    
    ofParameter<bool> clearCanvasBtn;
    ofParameterGroup brushSettings;
    ofParameter<ofColor> brushColor;
    ofParameter<int> brushStrokeW;

    
    brush(){
        isActive = false;
        
        gui.setup("settings");
        
        brushSettings.setName("Brush Settings");
        brushSettings.add(brushColor.set("Brush Color",ofColor(0,0,0),ofColor(0,0),ofColor(255,255)));
        brushSettings.add(brushStrokeW.set("Stroke Weight",20,1,60));
        brushSettings.add(clearCanvasBtn.set("Clear Canvas",false));
        
        clearCanvasBtn.addListener(this, &brush::ClearCanvasHandler);
        
        gui.add(brushSettings);

    }
    ~brush(){}
    
    void draw() {
        for (int j = 0; j < points.size(); j++) {
            
            
            // re draw mesh again
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            ofPushStyle();
            float r = ofMap(brushColor->r,0,255,0.0,1.0);
            float g = ofMap(brushColor->g,0,255,0.0,1.0);
            float b = ofMap(brushColor->b,0,255,0.0,1.0);
            
            ofSetColor(brushColor->r, brushColor->g, brushColor->b);
            
            
            
            for(int i = 1; i < points[j].size(); i++){
                
                thisPoint = points[j][i-1];
                nextPoint = points[j][i];
                
                
                
                
                ofVec3f direction = (nextPoint - thisPoint);
                
                float distance = direction.length();
                
                ofVec3f unitDirection = direction.getNormalized();
                
                ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
                ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
                
                float thickness = ofMap(distance, 0, 60, brushStrokeW, 2, true);
                
                leftPoint = thisPoint+toTheLeft*thickness;
                rightPoint = thisPoint+toTheRight*thickness;
                
                //mesh.clearColors();
                
                
                //mesh.setColor(mesh.getIndices()[i], ofFloatColor(r,g,b));
                mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y,0));
                mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, 0));
                
                //cout << "Color " << mesh.getColor() << endl;
            }
            
            
            //end the shape
            mesh.draw();
            // mesh.drawWireframe();
            ofPopStyle();
        }
        
        
        
        gui.draw();
    }
    
    void setNewStroke() {
        points.resize(points.size() + 1);
    }
    
    void setDraggingPoints(float _x, float _y) {
        points[points.size() - 1].push_back(ofVec2f(_x,_y));
    }
    
    void setReleased() {
        nthStroke.push_back(points.size());
    }
    
    void ClearCanvasHandler(bool & val){
        
        for (int j = 0; j < points.size(); j++) {
            
            
            for(int i = 1; i < points[j].size(); i++){
                points[j].clear();
            }
            
        }
        
        points.clear();

        
    }
};

#endif /* brush_h */
