import Ember from 'ember';

export default Ember.Controller.extend({
  actions: {
    go: function() {
      this.transitionToRoute("/url-two");
    }
  },

  // initital callbacks
  init()             { console.warn("controllers.index::init called"); this._super(...arguments); },
  didReceiveAttrs()  { console.warn("controllers.index::didReceiveAttrs called"); },
  willRender()       { console.warn("controllers.index::willRender called"); },
  didInsertElement() { console.warn("controllers.index::didInsertElement called"); },
  didRender()        { console.warn("controllers.index::didRender called"); },

  // re-renders

  didUpdateAttrs()   { console.warn("controllers.index::didUpdateAttrs called"); },
  // didReceiveAttrs:  function() { console.warn("controllers.index::didReceiveAttrs called"); },
  willUpdate()       { console.warn("controllers.index::willUpdate called"); },
  // willRender:       function() { console.warn("controllers.index::willRender called"); },
  didUpdate()        { console.warn("controllers.index::didUpdate called"); },
  // didRender:        function() { console.warn("controllers.index::didRender called"); },

});
