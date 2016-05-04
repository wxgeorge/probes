import Ember from 'ember';

export default Ember.Controller.extend({
  actions: {
    return: function() {
      this.transitionToRoute('/');
    },
  },

  // initital callbacks
  init()             { console.warn("controllers.url-two::init called"); this._super(...arguments); },
  didReceiveAttrs()  { console.warn("controllers.url-two::didReceiveAttrs called"); },
  willRender()       { console.warn("controllers.url-two::willRender called"); },
  didInsertElement() { console.warn("controllers.url-two::didInsertElement called"); },
  didRender()        { console.warn("controllers.url-two::didRender called"); },

  // re-renders

  didUpdateAttrs()   { console.warn("controllers.url-two::didUpdateAttrs called"); },
  // didReceiveAttrs:  function() { console.warn("controllers.url-two::didReceiveAttrs called"); },
  willUpdate()       { console.warn("controllers.url-two::willUpdate called"); },
  // willRender:       function() { console.warn("controllers.url-two::willRender called"); },
  didUpdate()        { console.warn("controllers.url-two::didUpdate called"); },
  // didRender:        function() { console.warn("controllers.url-two::didRender called"); },

});
