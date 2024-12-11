class CannotStartMovementException extends Error {
    constructor(message) {
        super(message);
        this.name = this.constructor.name;
    }
}

// Пример использования:
try {
    throw new CannotStartMovementException("Не удается начать движение");
} catch (error) {
    console.log(error.name);
    console.log(error.message);
}

export { CannotStartMovementException };