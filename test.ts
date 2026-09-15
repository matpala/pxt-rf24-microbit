rf24.begin()

input.onButtonPressed(Button.A, function () {
    rf24.sendNumber(42)
    basic.showIcon(IconNames.Yes)
})
