#include "fc.hpp"
#include "dsp/digital.hpp"


struct R : Module {
	enum ParamIds {
		POT2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN3b_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		NUM_OUTPUTS
	};
    enum LightIds {
		NUM_LIGHTS
	};



	R() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {reset();}
	void step() override;

	void reset() override {}


};


void R::step() {


	outputs[OUT1_OUTPUT].value = inputs[IN1_INPUT].value/10;
////////////////////////////////////////////////////

	outputs[OUT2_OUTPUT].value = (1-params[POT2_PARAM].value)*inputs[IN2_INPUT].value;
////////////////////////////////////////////////////

	outputs[OUT3_OUTPUT].value = inputs[IN3b_INPUT].value*inputs[IN3_INPUT].value;


}



struct RWidget : ModuleWidget {
	RWidget(R *module);
};

RWidget::RWidget(R *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/R.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));

    

	addInput(Port::create<PJ301MPort>(Vec(3, 296), Port::INPUT, module, R::IN1_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 296), Port::OUTPUT, module, R::OUT1_OUTPUT));

	addInput(Port::create<PJ301MPort>(Vec(3, 216), Port::INPUT, module, R::IN2_INPUT));
	addParam(ParamWidget::create<Trimpot>(Vec(20, 160), module, R::POT2_PARAM, 0.0f, 1.0f, 0.0f));
	addOutput(Port::create<PJ301MPort>(Vec(32, 216), Port::OUTPUT, module, R::OUT2_OUTPUT));

	addInput(Port::create<PJ301MPort>(Vec(3, 113), Port::INPUT, module, R::IN3_INPUT));
	addInput(Port::create<PJ301MPort>(Vec(3, 53), Port::INPUT, module, R::IN3b_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 113), Port::OUTPUT, module, R::OUT3_OUTPUT));



}

Model *modelR = Model::create<R, RWidget>("fc", "R", "R", UTILITY_TAG);
