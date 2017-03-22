Flicker
=======

This is a small test project that shows how components may be composed
in Unreal Engine. I wrote it in in response to an [answerhub post](https://answers.unrealengine.com/questions/577834/questions-about-the-workflow-of-using-components.html).

The project defines two components: an `UFlickerChildrenComponent` that causes any number of lights attached as children to periodically turn on and off, and an `UChangeColorComponent` that causes its parent component to change color, provided it is a light.

