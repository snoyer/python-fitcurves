from typing import Optional

from fitcurves_graphicgems import FitCurve  # type: ignore


def fit_curves(
    points: list[complex], sq_error: float, max_points: Optional[int] = None
) -> list[tuple[complex, complex, complex, complex]]:
    if not max_points:
        max_points = len(points)
    return FitCurve(points, sq_error, max_points)  # type: ignore
