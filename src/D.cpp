#include "fc.hpp"
#include "dsp/digital.hpp"


struct D : Module {
	enum ParamIds {
		POT_PARAM,
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
		LED3_LIGHT,
		NUM_LIGHTS
	};



	D() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {reset();}
	void step() override;

	void reset() override {}


};


void D::step() {

	if (inputs[IN1_INPUT].value>0) 
			outputs[OUT1_OUTPUT].value = inputs[IN1_INPUT].value;
		else outputs[OUT1_OUTPUT].value = 0.0f;
////////////////////////////////////////////////////

	if (inputs[IN2_INPUT].value<0) 
			outputs[OUT2_OUTPUT].value = inputs[IN2_INPUT].value;
		else outputs[OUT2_OUTPUT].value = 0.0f;
////////////////////////////////////////////////////

	if (inputs[IN3_INPUT].value>0) {
			outputs[OUT3_OUTPUT].value = inputs[IN3_INPUT].value;
			lights[LED3_LIGHT].value= inputs[IN3_INPUT].value/10.0f;
		}
		else {
			outputs[OUT3_OUTPUT].value = 0.0f;
			lights[LED3_LIGHT].value= 0.0f;
		}

}



struct DWidget : ModuleWidget {
	DWidget(D *module);
};

DWidget::DWidget(D *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/D.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
	//addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));

    

	addInput(Port::create<PJ301MPort>(Vec(3, 296), Port::INPUT, module, D::IN1_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 296), Port::OUTPUT, module, D::OUT1_OUTPUT));

	addInput(Port::create<PJ301MPort>(Vec(3, 216), Port::INPUT, module, D::IN2_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 216), Port::OUTPUT, module, D::OUT2_OUTPUT));

	addInput(Port::create<PJ301MPort>(Vec(3, 113), Port::INPUT, module, D::IN3_INPUT));
	addOutput(Port::create<PJ301MPort>(Vec(32, 113), Port::OUTPUT, module, D::OUT3_OUTPUT));
	addChild(ModuleLightWidget::create<MediumLight<BlueLight>>(Vec(26, 59), module, D::LED3_LIGHT));


}

Model *modelD = Model::create<D, DWidget>("fc", "D", "D", UTILITY_TAG);
