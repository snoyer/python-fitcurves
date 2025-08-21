from setuptools import Extension, setup

setup(
    name="fitcurves",
    version="0.0.1",
    description=(
        "An Algorithm for Automatically Fitting Digitized Curves"
        " by Philip J. Schneider,"
        ' from "Graphics Gems", Academic Press, 1990'
    ),
    packages=[
        "fitcurves",
    ],
    python_requires=">=3.9.0",
    ext_modules=[
        Extension(
            "fitcurves_graphicgems",
            [
                "pymodule.c",
                "gems/FitCurves.c",
                "gems/GraphicsGems.c",
            ],
            extra_compile_args=["-Wl,--no-undefined", "-O3", "-std=c99"],
        )
    ],
)
