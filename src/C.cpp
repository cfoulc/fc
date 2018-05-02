#include "fc.hpp"
#include "dsp/digital.hpp"


struct C : Module {
	enum ParamIds {
		POT2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT3b_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

float CHARGE1 = 0.0 ;
bool TRIGGER1 = false ;
float CHARGE2 = 0.0 ;
bool TRIGGER2 = false ;

	C() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {reset();}
	void step() override;

	void reset() override {}


};


void C::step() {

	CHARGE1 = CHARGE1 + inputs[IN1_INPUT].value/10000;
	if (CHARGE1 > 10.0) {
			TRIGGER1=true;
		}
	if (TRIGGER1) {
			outputs[OUT1_OUTPUT].value = CHARGE1;
			CHARGE1=CHARGE1 /1.01;
			if (CHARGE1<0.1) TRIGGER1=false ;
		}
////////////////////////////////////////////////////

	CHARGE2 = CHARGE2 + inputs[IN2_INPUT].value/10000;
	if (CHARGE2 > 10.0) {
			TRIGGER2=true;
		}
	if (TRIGGER2) {
			outputs[OUT2_OUTPUT].value = CHARGE1;
			CHARGE2=CHARGE2 /(1.01*(1-params[POT2_PARAM].value));
			if (CHARGE2<0.1) TRIGGER2=false ;
		}
////////////////////////////////////////////////////

	outputs[OUT3_OUTPUT].value = 10.0f;
	outputs[OUT3b_OUTPUT].value = -10.0f;


}



struct CWidget : ModuleWidget {
	CWidget(C *module);
};

CWidget::CWidget(C *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/C.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));

    

	addInput(Port::create<PJ301MPort>(Vec(3, 296), Port::INPUT, module, C::IN1_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 296), Port::OUTPUT, module, C::OUT1_OUTPUT));

	addInput(Port::create<PJ301MPort>(Vec(3, 216), Port::INPUT, module, C::IN2_INPUT));
	addParam(ParamWidget::create<Trimpot>(Vec(20, 160), module, C::POT2_PARAM, 0.0f, 1.0f, 0.0f));
	addOutput(Port::create<PJ301MPort>(Vec(32, 216), Port::OUTPUT, module, C::OUT2_OUTPUT));

	addOutput(Port::create<PJ301MPort>(Vec(3, 113), Port::OUTPUT, module, C::OUT3_OUTPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 113), Port::OUTPUT, module, C::OUT3b_OUTPUT));


}

Model *modelC = Model::create<C, CWidget>("fc", "C", "C", UTILITY_TAG);
